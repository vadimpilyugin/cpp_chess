#include "serialize.h"

void SerializedObject::add (std::string param) {
	serialized_obj += param;
	serialized_obj += DELIM;
}
std::string SerializedObject::get () {
	size_t delim_place = serialized_obj.find (DELIM);
	if (delim_place == std::string::npos) {
		return EMPTY;
	}
	std::string param_value = serialized_obj.substr (0, delim_place);
	serialized_obj.erase (0, delim_place + 1);
	return param_value;
}


const std::string SerializedObject::DELIM = std::string(";");
const std::string SerializedObject::EMPTY = std::string("");