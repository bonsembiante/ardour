#ifndef _ardour_vst3_plugin_debug_h_
#define _ardour_vst3_plugin_debug_h_

#include "ardour/libardour_visibility.h"
#include "ardour/plugin.h"
#include "ardour/vst3_host.h"

namespace ARDOUR {

using namespace Steinberg;
using namespace Steinberg::Vst;


class LIBARDOUR_API VSTEditControllerDebugger : public IEditController
{
public:
	VSTEditControllerDebugger (IEditController*);
	~VSTEditControllerDebugger ();

    void debug(std::string log);

    // From IEditController
	tresult PLUGIN_API setComponentState (IBStream* state);
	tresult PLUGIN_API setState (IBStream* state);
	tresult PLUGIN_API getState (IBStream* state);
	int32 PLUGIN_API getParameterCount ();
	tresult PLUGIN_API getParameterInfo (int32 paramIndex, ParameterInfo& info);
	tresult PLUGIN_API getParamStringByValue (ParamID id, ParamValue valueNormalized, String128 string);
	tresult PLUGIN_API getParamValueByString (ParamID id, TChar* string, ParamValue& valueNormalized);
	ParamValue PLUGIN_API normalizedParamToPlain (ParamID id, ParamValue valueNormalized);
	ParamValue PLUGIN_API plainParamToNormalized (ParamID id, ParamValue plainValue);
	ParamValue PLUGIN_API getParamNormalized (ParamID id);
	tresult PLUGIN_API setParamNormalized (ParamID id, ParamValue value);
	tresult PLUGIN_API setComponentHandler (IComponentHandler* handler);
	IPlugView* PLUGIN_API createView (FIDString name);

    // From IPluginBase
	tresult PLUGIN_API initialize (FUnknown* context);
	tresult PLUGIN_API terminate ();

    // From FUnknown
	tresult PLUGIN_API queryInterface (const TUID _iid, void** obj);
	uint32 PLUGIN_API addRef ();
	uint32 PLUGIN_API release ();

private:
	IEditController* _controller;
};


} // namespace ARDOUR
#endif
