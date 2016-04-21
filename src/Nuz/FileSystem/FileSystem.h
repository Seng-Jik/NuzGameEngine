#pragma once
#include "../../../include/Nuz/FileSystem/FileSystem.h"
#include <vector>
#include <string>
namespace _Nuz{

	class FileSystem{
    private:
        std::map<std::string,std::shared_ptr<Nuz::IFileSource>> m_name_sources;
        std::map<std::string,std::shared_ptr<Nuz::IFileSource> > m_dir_sources;
	public:
		virtual void Mount(
				const std::string& name,
				const std::string& dir,
				std::shared_ptr<Nuz::IFileSource> source
		);
		virtual void Unmount(const std::string& name);
		virtual std::shared_ptr<std::vector<unsigned char>> LoadFile(const std::string& name) const;
	};
}
