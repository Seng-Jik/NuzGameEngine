#include "ImageCacheManager.h"
using namespace Nuz_::Renderer;

std::shared_ptr<Texture> Nuz_::Renderer::ImageCacheManager::LoadImage(const std::string & path)
{
	if (m_imageCache.count(path)) {
		if (!m_imageCache.at(path).expired())
			return m_imageCache.at(path).lock();
	}
	std::shared_ptr<Texture> ret(new Texture);
	ret->LoadImage(path);
	m_imageCache[path] = std::weak_ptr<Texture>(ret);
	return ret;
}

std::shared_ptr<Texture> Nuz_::Renderer::ImageCacheManager::RenderSurface(SDL_Surface * sur)
{
	std::shared_ptr<Texture> ret(new Texture);
	ret->LoadSurface(sur);
	return ret;
}
