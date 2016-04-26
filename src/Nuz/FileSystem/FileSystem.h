#pragma once
#include "../../../include/Nuz/FileSystem/FileSystem.h"
#include <set>
#include <string>
#include <vector>
namespace Nuz_{

	class FileSystem:public Nuz::IFileSystem{
    private:
        std::set<std::shared_ptr<Nuz::IFileSource> > m_sources;
	public:
		virtual void Mount(std::shared_ptr<Nuz::IFileSource> source);
		virtual std::shared_ptr<std::vector<unsigned char>> LoadFile(const std::string& path) const;
	};
}
