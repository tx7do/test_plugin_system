#pragma once

#include <boost/dll/config.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <cctype>

inline boost::filesystem::path drop_version(const boost::filesystem::path& lhs)
{
	boost::filesystem::path ext = lhs.filename().extension();
	if (ext.native().size() > 1 && std::isdigit(ext.string()[1]))
	{
		ext = lhs;
		ext.replace_extension().replace_extension().replace_extension();
		return ext;
	}

	return lhs;
}

inline bool is_shared_library(const std::string& s)
{
	return (s.find(".dll") != std::string::npos || s.find(".so") != std::string::npos
		|| s.find(".dylib") != std::string::npos)
		&& s.find(".lib") == std::string::npos
		&& s.find(".exp") == std::string::npos
		&& s.find(".pdb") == std::string::npos
		&& s.find(".manifest") == std::string::npos
		&& s.find(".rsp") == std::string::npos
		&& s.find(".obj") == std::string::npos
		&& s.find(".a") == std::string::npos;
}

inline bool is_shared_library(const char* p)
{
	return is_shared_library(std::string(p));
}

inline bool is_shared_library(const boost::filesystem::path& p)
{
	return is_shared_library(p.string());
}

inline boost::dll::fs::path first_lib_from_argv(int argc, char* argv[])
{
	BOOST_ASSERT(argc > 1);
	(void)argc;

	for (int i = 1; i < argc; ++i)
	{
		if (is_shared_library(argv[i]))
		{
			return argv[i];
		}

		std::cout << "first_lib_from_argv(argc, argv): skipping '" << argv[i] << "'" << std::endl;
	}

	BOOST_ASSERT(false);
	return argv[1];
}

struct argv_to_path_guard
{
	const boost::filesystem::path original_;
	const boost::filesystem::path version_dropped_;
	const std::string just_path_;
	const bool same_;

	static inline boost::filesystem::path drop_b2_deco(const boost::filesystem::path& in)
	{
		std::size_t pos = in.filename().string().find("-");
		boost::filesystem::path
			res = in.parent_path() / in.filename().string().substr(0, in.filename().string().find("-"));
		if (pos != std::string::npos)
		{
			res += in.extension();
		}
		return res;
	}

	inline explicit argv_to_path_guard(int argc, char* argv[])
		: original_(first_lib_from_argv(argc,
		argv)), version_dropped_(drop_b2_deco(drop_version(original_))), just_path_(version_dropped_.parent_path()
		.string()), same_(version_dropped_ == original_)
	{
		if (!same_)
		{
			boost::system::error_code ignore;
			boost::filesystem::remove(version_dropped_, ignore);
			boost::filesystem::copy(original_, version_dropped_, ignore);
		}

		argv[1] = const_cast<char*>(just_path_.c_str());
	}

	inline ~argv_to_path_guard()
	{
		if (!same_)
		{
			boost::system::error_code ignore;
			boost::filesystem::remove(version_dropped_, ignore);
		}
	}
};
