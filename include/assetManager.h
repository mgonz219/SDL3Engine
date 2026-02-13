#pragma once
#include <iostream>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;
struct Renderer;
struct string;
struct Texture;

class AssetManager {
public:
    Texture& getTexture(Renderer& renderer, const std::string& path);

private:
    std::unordered_map<std::string, Texture> textures;
};
