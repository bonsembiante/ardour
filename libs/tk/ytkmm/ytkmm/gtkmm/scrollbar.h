// -*- c++ -*-
// Generated by gmmproc 2.45.3 -- DO NOT MODIFY!
#ifndef _GTKMM_SCROLLBAR_H
#define _GTKMM_SCROLLBAR_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* $Id: scrollbar.hg,v 1.1 2003/01/21 13:40:36 murrayc Exp $ */

/* scrollbar.h
 * 
 * Copyright (C) 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gtkmm/range.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkScrollbar GtkScrollbar;
typedef struct _GtkScrollbarClass GtkScrollbarClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class Scrollbar_Class; } // namespace Gtk
#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkVScrollbar GtkVScrollbar;
typedef struct _GtkVScrollbarClass GtkVScrollbarClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class VScrollbar_Class; } // namespace Gtk
#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkHScrollbar GtkHScrollbar;
typedef struct _GtkHScrollbarClass GtkHScrollbarClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class HScrollbar_Class; } // namespace Gtk
namespace Gtk
{

//TODO: Inherit/Implement Orientation when we can break ABI.

/** 
 * The Gtk::Scrollbar widget is an abstract base class for Gtk::HScrollbar
 * and Gtk::VScrollbar. It is not very useful in itself. 
 *
 * The position of the thumb in a scrollbar is controlled by the scroll
 * adjustments. See Gtk::Adjustment for the fields in an adjustment - for
 * Gtk::Scrollbar, the "value" field represents the position of the scrollbar,
 * which must be between the "lower" field and "upper - page_size." The
 * "page_size" field represents the size of the visible scrollable area. The
 * "step_increment" and "page_increment" fields are used when the user asks
 * to step down (using the small stepper arrows) or page down (using for
 * example the PageDown key).
 *
 * @ingroup Widgets
 */

class Scrollbar : public Range
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Scrollbar CppObjectType;
  typedef Scrollbar_Class CppClassType;
  typedef GtkScrollbar BaseObjectType;
  typedef GtkScrollbarClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~Scrollbar();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class Scrollbar_Class;
  static CppClassType scrollbar_class_;

  // noncopyable
  Scrollbar(const Scrollbar&);
  Scrollbar& operator=(const Scrollbar&);

protected:
  explicit Scrollbar(const Glib::ConstructParams& construct_params);
  explicit Scrollbar(GtkScrollbar* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkScrollbar*       gobj()       { return reinterpret_cast<GtkScrollbar*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkScrollbar* gobj() const { return reinterpret_cast<GtkScrollbar*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:


protected:
  

};

/** A vertical scrollbar.
 *
 * The Gtk::VScrollbar widget is a widget arranged vertically creating a
 * scrollbar. See Gtk::Scrollbar for details on scrollbars.
 *
 * A Gtk::Adjustment may may be passed to the constructor  to handle the
 * adjustment of the scrollbar. If not specified, one will be created for
 * you. See Gtk::Adjustment for details.
 *
 * @ingroup Widgets
 */

class VScrollbar : public Scrollbar
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef VScrollbar CppObjectType;
  typedef VScrollbar_Class CppClassType;
  typedef GtkVScrollbar BaseObjectType;
  typedef GtkVScrollbarClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~VScrollbar();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class VScrollbar_Class;
  static CppClassType vscrollbar_class_;

  // noncopyable
  VScrollbar(const VScrollbar&);
  VScrollbar& operator=(const VScrollbar&);

protected:
  explicit VScrollbar(const Glib::ConstructParams& construct_params);
  explicit VScrollbar(GtkVScrollbar* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkVScrollbar*       gobj()       { return reinterpret_cast<GtkVScrollbar*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkVScrollbar* gobj() const { return reinterpret_cast<GtkVScrollbar*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

public:
  VScrollbar();
  explicit VScrollbar(Adjustment& gtkadjustment);
  

};

/** A horizontal scrollbar.
 *
 * The Gtk::HScrollbar widget is a widget arranged horizontally creating a
 * scrollbar. See Gtk::Scrollbar for details on scrollbars.
 *
 * A Gtk::Adjustment may may be passed to the constructor  to handle the
 * adjustment of the scrollbar. If not specified, one will be created for
 * you. See Gtk::Adjustment for details.
 *
 * @ingroup Widgets
 */

class HScrollbar : public Scrollbar
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef HScrollbar CppObjectType;
  typedef HScrollbar_Class CppClassType;
  typedef GtkHScrollbar BaseObjectType;
  typedef GtkHScrollbarClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~HScrollbar();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class HScrollbar_Class;
  static CppClassType hscrollbar_class_;

  // noncopyable
  HScrollbar(const HScrollbar&);
  HScrollbar& operator=(const HScrollbar&);

protected:
  explicit HScrollbar(const Glib::ConstructParams& construct_params);
  explicit HScrollbar(GtkHScrollbar* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkHScrollbar*       gobj()       { return reinterpret_cast<GtkHScrollbar*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkHScrollbar* gobj() const { return reinterpret_cast<GtkHScrollbar*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

public:
  HScrollbar();
  explicit HScrollbar(Adjustment& gtkadjustment);
  

};


} /* namespace Gtk */


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::Scrollbar
   */
  Gtk::Scrollbar* wrap(GtkScrollbar* object, bool take_copy = false);
} //namespace Glib


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::VScrollbar
   */
  Gtk::VScrollbar* wrap(GtkVScrollbar* object, bool take_copy = false);
} //namespace Glib


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::HScrollbar
   */
  Gtk::HScrollbar* wrap(GtkHScrollbar* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_SCROLLBAR_H */

