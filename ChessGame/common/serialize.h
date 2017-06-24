#pragma once

#include <string>

class SerializedObject {
public:
	SerializedObject (std::string serialized_obj_ = std::string()): serialized_obj(serialized_obj_) {}
	void add (std::string param);
	std::string get ();
	std::string toString () const {
		return serialized_obj;
	}
private:
	std::string serialized_obj;
	static const std::string DELIM;
	static const std::string EMPTY;
};
