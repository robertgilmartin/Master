#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "glew-2.1.0/include/GL/glew.h"
#include "MemoryLeaks.h"

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}


bool ModuleTexture::Init()
{
	ilInit();
    iluInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	return true;
}


update_status ModuleTexture::Update()
{
    

	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	LOG("Destroying renderer");

	
	return true;
}

unsigned ModuleTexture::LoadTexture(const char* filename) 
{
    ILuint imageText;    

    ilGenImages(1, &imageText);
    ilBindImage(imageText);
    
    ILboolean success;
    
    unsigned textureID;
    textureName = filename;
    success = ilLoadImage(filename);
    if (success == IL_TRUE)
    {
        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    }
    if (success == IL_FALSE)
    {
        LOG("ERROR");
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    ILinfo info;

    iluGetImageInfo(&info);
    
    textureWidth = info.Width;
    textureHeight = info.Height;
    pixelDepht = info.Depth;
    textureFormat = info.Format;

    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
        ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
        ilGetData());

       

    //Mipmaping -->Editor --To do


    //Mag/min --> Editor to do
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    
    
    if (activeWrap)
    {
        if (wrapS)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        }
        if (wrapT)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        if (wrapR)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        }       
    }
    

    if (activeMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    

    ilDeleteImage(imageText);
    
    return textureID;
}
