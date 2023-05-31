#include "Texture2D.h"

#include "stb_image.h"

Texture2D* Texture2D::LoadFromFile(std::string& image_file_path)
{
    Texture2D* texture2d = new Texture2D();

    stbi_set_flip_vertically_on_load(true);
    int channels_in_file;
    unsigned char* data = stbi_load(image_file_path.c_str(), &(texture2d->width_), &(texture2d->height_), &channels_in_file, 0);
    if (data != nullptr)
    {
        switch (channels_in_file) {
        case 1:
        {
            texture2d->gl_texture_format_ = GL_ALPHA;
            break;
        }
        case 3:
        {
            texture2d->gl_texture_format_ = GL_RGB;
            break;
        }
        case 4:
        {
            texture2d->gl_texture_format_ = GL_RGBA;
            break;
        }
        }
    }

    stbi_image_free(data);

    return texture2d;
}