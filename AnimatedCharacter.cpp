#include <Urho3D/Resource/ResourceCache.h>

#include <Urho3D/Core/Context.h>

#include <Urho3D/Graphics/Material.h>

#include "AnimatedCharacter.h"

#include "dirent.h"

namespace Urho3D 
{

AnimatedCharacter::AnimatedCharacter (Context *context) : 
    LogicComponent(context)
{

}

void AnimatedCharacter::RegisterObject (Context *context)
{
    context->RegisterFactory<AnimatedCharacter>();
}

void AnimatedCharacter::OnNodeSet (Node *node)
{
    if (node == nullptr)
        return;

    /* face_detail_ = node->CreateComponent<AnimatedModel>(); */
    /* mouth_ = node->CreateComponent<AnimatedModel>(); */
    /* shirt_ = node->CreateComponent<AnimatedModel>(); */
    /* pants_ = node->CreateComponent<AnimatedModel>(); */
    /* hat_ = node->CreateComponent<AnimatedModel>(); */

    /* String mat = "unlit.xml"; */

    /* SetModel("chibi/body.mdl", BodyPart::Body); */
    /* SetModel("chibi/head.mdl", BodyPart::Head); */
    /* SetModel("chibi/eyes_1.mdl", BodyPart::Eyes); */
    /* SetModel("chibi/face_1.mdl", BodyPart::FaceDetail); */
    /* SetModel("chibi/mouth_1.mdl", BodyPart::Mouth); */

    /* SetModel("chibi/overalls.mdl", BodyPart::Shirt); */
    /* SetModel("chibi/tshirt.mdl", BodyPart::Shirt); */
/* //    SetModel("chibi/mouth_1.mdl", BodyPart::Mouth); */
/* //    SetModel("chibi/mouth_1.mdl", BodyPart::Mouth); */

    /* anim_ = node->CreateComponent<AnimationController>(); */
    /* anim_->Play("chibi/walk.ani", 1, true, 0.1f); */
}

/* void AnimatedCharacter::FixedUpdate (float time_step) */
/* { */
/*     // animate */
/* } */

void AnimatedCharacter::SetModel (String model_file_path)
{
    auto *cache = GetSubsystem<ResourceCache>();
    Model *model_res = cache->GetResource<Model>(model_file_path);

    if (!model_res)
    {
        return;
    }

    model_ = node_->CreateComponent<AnimatedModel>();
    model_->SetModel(cache->GetResource<Model>(model_file_path));

    FindAnimationFiles(model_file_path);


    /* if (material_file_path == "") */
    /* { */
    /*     Vector<String> parts = model_file_path.Split('.'); */

    /*     for (int p = 0; p < parts.Size() - 1; p ++) */
    /*     { */
    /*         material_file_path += parts[p]; */
    /*     } */

    /*     material_file_path += ".xml"; */
    /* } */

    /* Material *mat = cache->GetResource<Material>(material_file_path); */

    /* if (!mat) */
    /* { */
    /*     return; */
    /* } */

    /* switch (part) */
    /* { */
    /*     case BodyPart::Head: */
    /*         model = head_; */
    /*         break; */
    /*     case BodyPart::Eyes: */
    /*         model = eyes_; */
    /*         break; */
    /*     case BodyPart::Mouth: */
    /*         model = mouth_; */
    /*         break; */
    /*     case BodyPart::FaceDetail: */
    /*         model = face_detail_; */
    /*         break; */
    /*     case BodyPart::Shirt: */
    /*         model = shirt_; */
    /*         break; */
    /*     case BodyPart::Pants: */
    /*         model = pants_; */
    /*         break; */
    /*     case BodyPart::Hat: */
    /*         model = hat_; */
    /*         break; */
    /*     default: */
    /*         model = body_; */
    /*         break; */
    /* } */

    /* model->SetModel(model_res); */
    /* model->SetCastShadows(true); */
    /* model->SetMaterial(mat); */
}

void AnimatedCharacter::FindAnimationFiles (String filepath)
{
    auto *cache = GetSubsystem<ResourceCache>();
    DIR *dir;
    String dir_path;
    Vector<String> parts;
    dirent *ent;

    printf("loading animations from %s\n", dir_path.CString());

    parts = filepath.Split('/');
    parts.Erase(parts.Size() - 1);
    dir_path.Join(parts, "/");
    dir = opendir(dir_path.CString());

    while ((ent = readdir(dir)) != NULL)
    {
        LoadAnimationFile(dir_path + ent->d_name);
    }

    closedir(dir);
}

void AnimatedCharacter::LoadAnimationFile (String filepath)
{
    printf("load anim : %s\n", filepath.CString());
}

};
