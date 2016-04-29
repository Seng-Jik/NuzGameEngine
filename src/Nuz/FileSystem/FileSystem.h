#pragma once
#include "../../../include/Nuz/FileSystem/FileSystem.h"
#include <set>
#include <string>
#include <map>
#include <vector>
#include <mutex>

namespace Nuz_{

	class FileSystem:public Nuz::IFileSystem{
    private:
        std::map<std::string,std::shared_ptr<const Nuz::IFileSource> > m_sources;
	public:
        void Mount(const std::shared_ptr<const Nuz::IFileSource>& source,const std::string& dir = "") override;
        std::shared_ptr<std::vector<uint8_t>> LoadFile(const std::string& path) const override;
	};
}
