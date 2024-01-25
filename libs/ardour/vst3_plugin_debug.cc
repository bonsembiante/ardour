#include "ardour/vst3_plugin_debug.h"

using namespace ARDOUR;
using namespace Steinberg;
using namespace Steinberg::Vst;

const char * VST3_PLUGIN_DEBUG_FLAG = "VST3_CONTROLLER";

VSTEditControllerDebugger::VSTEditControllerDebugger (IEditController* editController){
	_controller = editController;
}

VSTEditControllerDebugger::~VSTEditControllerDebugger (){
	_controller = 0;
}

void VSTEditControllerDebugger::debug(std::string log) {
	printf("%s", log.c_str());
}

tresult VSTEditControllerDebugger::setComponentState (IBStream* state){
	debug("CUSTOM WRAPPER CALL: _controller->setComponentState (state)");
	return _controller->setComponentState (state);
}

tresult VSTEditControllerDebugger::setState (IBStream* state){
	debug("CUSTOM WRAPPER CALL: _controller->setState (state)");
	return _controller->setState (state);
}

tresult VSTEditControllerDebugger::getState (IBStream* state){
	debug("CUSTOM WRAPPER CALL: _controller->getState (state)");
	return _controller->getState (state);
}

int32 VSTEditControllerDebugger::getParameterCount (){
	debug("CUSTOM WRAPPER CALL: _controller->getParameterCount ()");
	return _controller->getParameterCount ();
}

tresult VSTEditControllerDebugger::getParameterInfo (int32 paramIndex, ParameterInfo& info /*out*/){
	debug("CUSTOM WRAPPER CALL: _controller->getParameterInfo (paramIndex, info)");
	return _controller->getParameterInfo (paramIndex, info);
}

tresult VSTEditControllerDebugger::getParamStringByValue (ParamID id, ParamValue valueNormalized /*in*/, String128 string /*out*/){
	debug("CUSTOM WRAPPER CALL: _controller->getParamStringByValue (id, valueNormalized, string)");
	return _controller->getParamStringByValue (id, valueNormalized, string);
}

tresult VSTEditControllerDebugger::getParamValueByString (ParamID id, TChar* string /*in*/, ParamValue& valueNormalized /*out*/){
	debug("CUSTOM WRAPPER CALL: _controller->getParamValueByString (id, string, valueNormalized)");
	return _controller->getParamValueByString (id, string, valueNormalized);
}

ParamValue VSTEditControllerDebugger::normalizedParamToPlain (ParamID id, ParamValue valueNormalized){
	debug("CUSTOM WRAPPER CALL: _controller->normalizedParamToPlain (id, valueNormalized)");
	return _controller->normalizedParamToPlain (id, valueNormalized);
}

ParamValue VSTEditControllerDebugger::plainParamToNormalized (ParamID id, ParamValue plainValue){
	debug("CUSTOM WRAPPER CALL: _controller->plainParamToNormalized (id, plainValue)");
	return _controller->plainParamToNormalized (id, plainValue);
}

ParamValue VSTEditControllerDebugger::getParamNormalized (ParamID id){
	debug("CUSTOM WRAPPER CALL: _controller->getParamNormalized (id)");
	return _controller->getParamNormalized (id);
}

tresult VSTEditControllerDebugger::setParamNormalized (ParamID id, ParamValue value){
	debug("CUSTOM WRAPPER CALL: _controller->setParamNormalized (id, value)");
	return _controller->setParamNormalized (id, value);
}

tresult VSTEditControllerDebugger::setComponentHandler (IComponentHandler* handler){
	debug("CUSTOM WRAPPER CALL: _controller->setComponentHandler (handler)");
	return _controller->setComponentHandler (handler);
}

IPlugView* VSTEditControllerDebugger::createView (FIDString name){
	debug("CUSTOM WRAPPER CALL: _controller->createView (name)");
	return _controller->createView (name);
}

tresult VSTEditControllerDebugger::initialize (FUnknown* context){
	debug("CUSTOM WRAPPER CALL: _controller->initialize (context)");
	return _controller->initialize (context);
}

tresult VSTEditControllerDebugger::terminate (){
	debug("CUSTOM WRAPPER CALL: _controller->terminate ()");
	return _controller->terminate ();
}

tresult VSTEditControllerDebugger::queryInterface (const TUID _iid, void** obj){
	debug("CUSTOM WRAPPER CALL: _controller->queryInterface (_iid, obj)");
	return _controller->queryInterface (_iid, obj);
}

uint32 VSTEditControllerDebugger::addRef (){
	debug("CUSTOM WRAPPER CALL: _controller->addRef ()");
	return _controller->addRef ();
}

uint32 VSTEditControllerDebugger::release (){
	debug("CUSTOM WRAPPER CALL: _controller->release ()");
	return _controller->release ();
}
