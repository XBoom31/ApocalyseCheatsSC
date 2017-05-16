#pragma once
class SkinC
{
public:
	SkinC();
	~SkinC();
	bool Load(const std::string& gamePath, const std::string& gameShortName);
	struct SkinInfo_t
	{
		unsigned int	_id;			// index u know for what
		std::string		_shortname;		// shortname
		std::string		_name;			// full skin name
	};

};

