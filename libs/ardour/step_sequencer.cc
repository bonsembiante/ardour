/*
 * Copyright (C) 2018 Paul Davis <paul@linuxaudiosystems.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <cassert>

#include "pbd/i18n.h"

#include "ardour/audioengine.h"
#include "ardour/midi_buffer.h"
#include "ardour/midi_state_tracker.h"
#include "ardour/step_sequencer.h"
#include "ardour/tempo.h"

using namespace PBD;
using namespace ARDOUR;
using namespace std;

Step::Step (StepSequence &s, size_t n, Temporal::Beats const & b, int base_note)
	: _sequence (s)
	, index (n)
	, _enabled (true)
	, _nominal_beat (b)
	, _skipped (false)
	, _mode (AbsolutePitch)
	, _octave_shift (0)
	, _duration (1)
{
	_notes[0].number = base_note;

	for (size_t n = 1; n < _notes_per_step; ++n) {
		_notes[n].number = -1;
	}


	for (size_t n = 0; n < _parameters_per_step; ++n) {
		_parameters[n].parameter = -1;
	}
}

Step::~Step ()
{
}

StepSequencer&
Step::sequencer() const
{
	return _sequence.sequencer();
}

void
Step::set_mode (Mode m)
{
	_mode = m;
}

void
Step::set_beat (Temporal::Beats const & b)
{
	_nominal_beat = b;
}

void
Step::set_note (double note, double velocity, int n)
{
	assert (n < _notes_per_step);
	_notes[n].number = note;
	_notes[n].velocity = velocity;
}

void
Step::set_velocity (double velocity, size_t n)
{
	assert (n < _notes_per_step);

	if (_notes[n].velocity != velocity) {
		_notes[n].velocity = velocity;

		PropertyChange pc;
		PropertyChanged (pc);
	}
}

void
Step::set_octave_shift (int s)
{
	if (s > 4) {
		s = 4;
	} else if (s < -4) {
		s = -4;
	}

	if (s == _octave_shift) {
		return;
	}

	_octave_shift = s;

	PropertyChange pc;
	PropertyChanged (pc);
}

void
Step::set_chord (size_t note_cnt, double* notes)
{
}

void
Step::set_parameter (int number, double value, int n)
{
	assert (n < _parameters_per_step);
	_parameters[n].parameter = number;
	_parameters[n].value = value;
}

void
Step::set_enabled (bool yn)
{
	_enabled = yn;
}

void
Step::adjust_duration (DurationRatio const & amt)
{
	set_duration (_duration + amt);
}

void
Step::set_duration (DurationRatio const & dur)
{
	if (dur > 1.0) {
		_duration = DurationRatio (1);
	} else if (dur < DurationRatio()) {
		_duration = DurationRatio ();
	} else {
		_duration = dur;
	}

	PropertyChange pc;
	PropertyChanged (pc);
}

void
Step::adjust_pitch (int amt)
{
	Step::Note& note (_notes[0]);

	note.number += amt;

	if (note.number > 127.0) {
		note.number = 127.0;
	}

	if (note.number < 0.0) {
		note.number = 0.0;
	}

	PropertyChange pc;
	PropertyChanged (pc);
}

void
Step::adjust_velocity (int amt)
{
	Step::Note& note (_notes[0]);

	note.velocity += (1.0/128.0) * amt;

	if (note.velocity > 1.0) {
		note.velocity = 1.0;
	}

	if (note.velocity < 0.0) {
		note.velocity = 0.0;
	}

	PropertyChange pc;
	PropertyChanged (pc);
}

void
Step::adjust_octave (int amt)
{
	set_octave_shift (_octave_shift + amt);
}

bool
Step::run (MidiBuffer& buf, bool running, samplepos_t start_sample, samplepos_t end_sample, MidiStateTracker&  tracker)
{
	for (size_t n = 0; n < _notes_per_step; ++n) {
		check_parameter (n, buf, running, start_sample, end_sample);
	}

	for (size_t n = 0; n < _notes_per_step; ++n) {
		check_note (n, buf, running, start_sample, end_sample, tracker);
	}

	if (running) {

		samplepos_t scheduled_samples = sequencer().tempo_map().sample_at_beat (_scheduled_beat.to_double());

		if (scheduled_samples >= start_sample && scheduled_samples < end_sample) {
			/* this step was covered by the run() range, so update its next
			 *  scheduled time.
			 */
			_scheduled_beat += sequencer().duration();
		}

	}

	return true;
}

void
Step::check_parameter (size_t n, MidiBuffer& buf, bool running, samplepos_t start_sample, samplepos_t end_sample)
{
}

void
Step::check_note (size_t n, MidiBuffer& buf, bool running, samplepos_t start_sample, samplepos_t end_sample, MidiStateTracker& tracker)
{
	Note& note (_notes[n]);

	/* could be a note off message to be delivered before any note on
	 * message (and the note number may differ from the current value.
	 * Deliver it now, if appropriate.
	 */

	if (note.on) {

		samplepos_t off_samples = sequencer().tempo_map().sample_at_beat (note.off_at.to_double());

		if (off_samples >= start_sample && off_samples < end_sample) {

			buf.write (off_samples - start_sample, Evoral::MIDI_EVENT, 3, note.off_msg);
			tracker.remove (note.off_msg[1], _sequence.channel());

			/* record keeping */

			note.on = false;
			note.off_at = Temporal::Beats();
		}

		/* XXX we should possibly queue these note offs */

	}

	if (_duration == DurationRatio ()) {
		/* no duration, so no new notes on */
		return;
	}

	if (note.number < 0) {
		/* note not set .. ignore */
		return;
	}

	/* figure out when this note would sound */

	Temporal::Beats note_on_time = _scheduled_beat;

	note_on_time += note.offset;

	if (running && !note.on) {

		/* don't play silent notes */

		if (note.velocity == 0) {
			return;
		}

		samplepos_t on_samples = sequencer().tempo_map().sample_at_beat (note_on_time.to_double());

		if (on_samples >= start_sample && on_samples < end_sample) {

			uint8_t mbuf[3];

			/* prepare 3 MIDI bytes for note on */

			mbuf[0] = 0x90 | _sequence.channel();

			switch (_mode) {
			case AbsolutePitch:
				mbuf[1] = note.number;
				break;
			case RelativePitch:
				mbuf[1] = _sequence.root() + note.interval;
				break;
			}

			if (_octave_shift) {

				const int t = mbuf[1] + (12 * _octave_shift);

				if (t > 127 || t < 0) {
					/* Out of range */
					return;
				}

				mbuf[1] = t;
			}

			mbuf[2] = (uint8_t) floor (note.velocity * 127.0);

			note.off_msg[0] = 0x80 | _sequence.channel();
			note.off_msg[1] = mbuf[1];
			note.off_msg[2] = mbuf[2];

			/* Put it into the MIDI buffer */
			buf.write (on_samples - start_sample, Evoral::MIDI_EVENT, 3, mbuf);
			tracker.add (mbuf[1], _sequence.channel());

			/* keep track (even though other things will at different levels */

			note.on = true;

			/* compute note off time based on our duration */

			note.off_at = note_on_time;

			if (_duration == DurationRatio (1)) {
				/* use 1 tick less than the sequence step size
				 * just to get non-simultaneous on/off events at
				 * step boundaries.
				*/
				note.off_at += Temporal::Beats (0, sequencer().step_size().to_ticks() - 1);
			} else {
				note.off_at += Temporal::Beats (0, (sequencer().step_size().to_ticks() * _duration.numerator()) / _duration.denominator());
			}
		}
	}

	/* if the buffer size is large and the step size or note length is very
	 * small, the note off could be within the same ::run() cycle as the
	 * note on. So check again to see if we should deliver it in this same
	 * ::run() cycle.
	 */

	if (note.on) {

		samplepos_t off_samples = sequencer().tempo_map().sample_at_beat (note.off_at.to_double());

		if (off_samples >= start_sample && off_samples < end_sample) {

			buf.write (off_samples - start_sample, Evoral::MIDI_EVENT, 3, note.off_msg);
			tracker.remove (note.off_msg[1], _sequence.channel());

			/* record keeping */

			note.on = false;
			note.off_at = Temporal::Beats();
		}
	}
}

void
Step::reschedule (Temporal::Beats const & start, Temporal::Beats const & offset)
{
	if (_nominal_beat < offset) {
		_scheduled_beat = start + _nominal_beat + sequencer().duration(); /* schedule into the next loop iteration */
	} else {
		_scheduled_beat = start + _nominal_beat; /* schedule into the current loop iteration */
	}

	/* MIDI state tracker will deal with any stuck notes, so here we just
	 * update our records to note that all notes are not currently
	 * sounding.
	 */
	for (size_t n = 0; n < _notes_per_step; ++n) {
		_notes[n].on = false;
		_notes[n].off_at = Temporal::Beats();
	}
}

XMLNode&
Step::get_state ()
{
	return *new XMLNode (X_("Step"));
}

int
Step::set_state (XMLNode const &, int)
{
	return 0;
}

/**/

StepSequence::StepSequence (StepSequencer& s, size_t cnt, size_t nsteps, Temporal::Beats const & step_size, Temporal::Beats const & bar_size, int r)
	: _sequencer (s)
	, _index (cnt)
	, _channel (0)
	, _root (r)
	, _mode (MusicalMode::IonianMajor)
{
	Temporal::Beats beats;

	for (size_t s = 0; s < nsteps; ++s) {
		/* beats is wrong but we will correct in ::schedule */
		_steps.push_back (new Step (*this, s, beats, _root));
	}

	/* schedule them all from zero for now */
	schedule (beats);
}

StepSequence::~StepSequence ()
{
	for (Steps::iterator i = _steps.begin(); i != _steps.end(); ++i) {
		delete *i;
	}
}

void
StepSequence::schedule (Temporal::Beats const & start)
{
	Temporal::Beats beats (start);
	const size_t s = _sequencer.start_step();
	const size_t e = _sequencer.end_step();

	for (size_t n = s; n < e; ++n) {
		_steps[n]->set_beat (beats);
		cerr << "beat " << n << " @ " << beats << ' ';
		beats += _sequencer.step_size();
	}
	cerr << endl;
}

void
StepSequence::reschedule (Temporal::Beats const & start, Temporal::Beats const & offset)
{
	const size_t s = _sequencer.start_step();
	const size_t e = _sequencer.end_step();

	for (size_t n = s; n < e; ++n) {
		_steps[n]->reschedule (start, offset);
	}
}

void
StepSequence::set_channel (int c)
{
	_channel = c;
}

bool
StepSequence::run (MidiBuffer& buf, bool running, samplepos_t start_sample, samplepos_t end_sample, MidiStateTracker& tracker)
{
	const size_t s = _sequencer.start_step();
	const size_t e = _sequencer.end_step();
	const size_t t = _steps.size();
	size_t n = 0;

	/* steps before the start step .. may still have pending off's or ... */

	while (n < s) {
		_steps[n++]->run (buf, false, start_sample, end_sample, tracker);
	}

	/* currently in use steps */

	while (n < e) {
		_steps[n++]->run (buf, running, start_sample, end_sample, tracker);
	}

	/* steps after the end step .. may still have pending off's or ... */

	while (n < t) {
		_steps[n++]->run (buf, false, start_sample, end_sample, tracker);
	}

	return true;
}

Step&
StepSequence::step (size_t n) const
{
	assert (n < _steps.size());
	return *_steps[n];
}


XMLNode&
StepSequence::get_state()
{
	return *new XMLNode (X_("StepSequence"));
}

int
StepSequence::set_state (XMLNode const &, int)
{
	return 0;
}

/**/

MultiAllocSingleReleasePool StepSequencer::Request::pool (X_("step sequencer requests"), sizeof (StepSequencer::Request), 64);

StepSequencer::StepSequencer (TempoMap& tmap, size_t nseqs, size_t nsteps, Temporal::Beats const & step_size, Temporal::Beats const & bar_size, int notenum)
	: _tempo_map (tmap)
	, _last_step (0)
	, _step_size (step_size)
	, _start_step (0)
	, _end_step (nsteps)
	, last_start (0)
	, last_end (0)
	, _running (false)
	, _step_capacity (nsteps)
	, requests (64)
{
	for (size_t n = 0; n < nseqs; ++n) {
		_sequences.push_back (new StepSequence (*this, n, nsteps, step_size, bar_size, notenum));
		notenum++;
	}
}

StepSequencer::~StepSequencer ()
{
	for (StepSequences::iterator i = _sequences.begin(); i != _sequences.end(); ++i) {
		delete *i;
	}
}

Temporal::Beats
StepSequencer::reschedule (samplepos_t start_sample)
{
	cerr << "SEQ reschedule\n";

	/* compute the beat position of this first "while-moving
	 * run() call as an offset into the sequencer's current loop
	 * length.
	 */

	const Temporal::Beats start_beat (_tempo_map.beat_at_sample (start_sample));
	const int32_t tick_duration = duration().to_ticks();

	const Temporal::Beats closest_previous_loop_start = Temporal::Beats::ticks ((start_beat.to_ticks() / tick_duration) * tick_duration);
	const Temporal::Beats offset = Temporal::Beats::ticks ((start_beat.to_ticks() % tick_duration));

	for (StepSequences::iterator s = _sequences.begin(); s != _sequences.end(); ++s) {
		(*s)->reschedule (closest_previous_loop_start, offset);
	}

	return closest_previous_loop_start;
}

bool
StepSequencer::run (MidiBuffer& buf, samplepos_t start_sample, samplepos_t end_sample, double speed, pframes_t, bool)
{
	Glib::Threads::Mutex::Lock lm (_sequence_lock);

	bool resolve = false;
	bool need_reschedule = check_requests ();

	if (speed == 0) {
		if (_running) {
			resolve = true;
			_running = false;
		}
	}

	if (speed != 0)  {

		if (!_running || (last_end != start_sample)) {

			if (last_end != start_sample) {
				/* non-linear motion, need to resolve notes */
				resolve = true;
			}

			_last_startup = reschedule (start_sample);
			last_start = start_sample;
			need_reschedule = false;
			_running = true;
		}
	}


	if (need_reschedule) {
		reschedule (start_sample);
		need_reschedule = false;
	}

	for (StepSequences::iterator s = _sequences.begin(); s != _sequences.end(); ++s) {
		(*s)->run (buf, _running, start_sample, end_sample, outbound_tracker);
	}

	const Temporal::Beats terminal_beat = Temporal::Beats (_tempo_map.beat_at_sample (end_sample - 1));
	const size_t dur_ticks = duration().to_ticks();
	const size_t step_ticks = _step_size.to_ticks();

	_last_step = _start_step + (((terminal_beat - _last_startup).to_ticks() % dur_ticks) / step_ticks);

	if (resolve) {
		outbound_tracker.resolve_notes (buf, 0);
	}

	last_start = start_sample;
	last_end = end_sample;

	return true;
}

int
StepSequencer::last_step () const
{
	return _last_step;
}

void
StepSequencer::sync ()
{
}

void
StepSequencer::reset ()
{
	{
		Glib::Threads::Mutex::Lock lm1 (_sequence_lock);
		for (StepSequences::iterator s = _sequences.begin(); s != _sequences.end(); ++s) {
			(*s)->reset ();
		}
	}
}

Temporal::Beats
StepSequencer::duration() const
{
	return _step_size * (_end_step - _start_step) ;
}

void
StepSequence::reset ()
{
}

StepSequence&
StepSequencer::sequence (size_t n) const
{
	assert (n < _sequences.size());
	return *_sequences[n];
}

void
StepSequencer::set_start_step (size_t n)
{
	Request* r = new Request;
	r->type = Request::SetStartStep;
	r->start_step = n;
	requests.write (&r, 1);
}

void
StepSequencer::set_end_step (size_t n)
{
	Request* r = new Request;
	r->type = Request::SetEndStep;
	r->end_step = n;
	requests.write (&r, 1);
}

XMLNode&
StepSequencer::get_state()
{
	return *new XMLNode (X_("StepSequencer"));
}

int
StepSequencer::set_state (XMLNode const &, int)
{
	return 0;
}

bool
StepSequencer::check_requests ()
{
	Request* req;
	bool changed = false;
	bool reschedule = false;

	while (requests.read (&req, 1)) {

		if (req->type & Request::SetStartStep) {
			if (req->start_step != _start_step) {
				if (req->start_step < _end_step) {
					_start_step = req->start_step;
					reschedule = true;
					changed = true;
				}
			}
		}

		if (req->type & Request::SetEndStep) {
			if (req->end_step != _end_step) {
				if (req->end_step > _start_step) {
					_end_step = req->end_step;
					reschedule = true;
					changed = true;
				}
			}
		}

		if (req->type & Request::SetNSequences) {
			// XXXX
		}
		if (req->type & Request::SetStepSize) {
			if (_step_size != req->step_size) {
				_step_size = req->step_size;
				reschedule = true;
				changed = true;
			}
		}
	}

	delete req;

	if (changed) {
		PropertyChange pc;
		PropertyChanged (pc);
	}

	return reschedule;
}