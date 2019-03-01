#include <Urho3D/Resource/ResourceCache.h>

#include <Urho3D/Core/Context.h>

#include <Urho3D/Graphics/Material.h>

#include "DynamicCharacter.h"

namespace bust
{

DynamicCharacter::DynamicCharacter (Context *context) : 
    LogicComponent(context)
{

}

void DynamicCharacter::RegisterObject (Context *context)
{
    context->RegisterFactory<DynamicCharacter>();
}

void DynamicCharacter::OnNodeSet (Node *node)
{
    if (node == nullptr)
        return;

    body_ = node->CreateComponent<AnimatedModel>();
    head_ = node->CreateComponent<AnimatedModel>();
    eyes_ = node->CreateComponent<AnimatedModel>();
    face_detail_ = node->CreateComponent<AnimatedModel>();
    mouth_ = node->CreateComponent<AnimatedModel>();
    shirt_ = node->CreateComponent<AnimatedModel>();
    pants_ = node->CreateComponent<AnimatedModel>();
    hat_ = node->CreateComponent<AnimatedModel>();

    String mat = "unlit.xml";

    SetModel("chibi/body.mdl", BodyPart::Body);
    SetModel("chibi/head.mdl", BodyPart::Head);
    SetModel("chibi/eyes_1.mdl", BodyPart::Eyes);
    SetModel("chibi/face_1.mdl", BodyPart::FaceDetail);
    SetModel("chibi/mouth_1.mdl", BodyPart::Mouth);

    SetModel("chibi/overalls.mdl", BodyPart::Shirt);
    SetModel("chibi/tshirt.mdl", BodyPart::Shirt);
//    SetModel("chibi/mouth_1.mdl", BodyPart::Mouth);
//    SetModel("chibi/mouth_1.mdl", BodyPart::Mouth);

    anim_ = node->CreateComponent<AnimationController>();
    anim_->Play("chibi/walk.ani", 1, true, 0.1f);
}

void DynamicCharacter::FixedUpdate (float time_step)
{
    // animate
}

void DynamicCharacter::SetModel (String model_file_path, 
        BodyPart part,
        String material_file_path)
{
    auto *cache = GetSubsystem<ResourceCache>();
    Model *model_res = cache->GetResource<Model>(model_file_path);

    if (!model_res)
    {
        return;
    }

    AnimatedModel *model;

    if (material_file_path == "")
    {
        Vector<String> parts = model_file_path.Split('.');

        for (int p = 0; p < parts.Size() - 1; p ++)
        {
            material_file_path += parts[p];
        }

        material_file_path += ".xml";
    }

    Material *mat = cache->GetResource<Material>(material_file_path);

    if (!mat)
    {
        return;
    }

    switch (part)
    {
        case BodyPart::Head:
            model = head_;
            break;
        case BodyPart::Eyes:
            model = eyes_;
            break;
        case BodyPart::Mouth:
            model = mouth_;
            break;
        case BodyPart::FaceDetail:
            model = face_detail_;
            break;
        case BodyPart::Shirt:
            model = shirt_;
            break;
        case BodyPart::Pants:
            model = pants_;
            break;
        case BodyPart::Hat:
            model = hat_;
            break;
        default:
            model = body_;
            break;
    }

    model->SetModel(model_res);
    model->SetCastShadows(true);
    model->SetMaterial(mat);
}

};
