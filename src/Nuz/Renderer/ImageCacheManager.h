#pragma once
#include <map>
#include <memory>
#include "OpenGL\Texture.h"
namespace Nuz_ {
	namespace Renderer {
		class ImageCacheManager
		{
		private:
			std::map<std::string, std::weak_ptr<Texture>> m_imageCache;
		public:
			std::shared_ptr<Texture> LoadImage(const std::string& path);
		};

	}
}
