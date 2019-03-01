#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>

using namespace Urho3D;

namespace bust
{

enum class BodyPart
{
    Head,
    Body,
    Eyes,
    Mouth,
    FaceDetail,

    Shirt,
    Pants,
    Hat,
};

class DynamicCharacter : public LogicComponent
{
URHO3D_OBJECT(DynamicCharacter, LogicComponent);

public:
    explicit DynamicCharacter (Context *context);
    static void RegisterObject (Context *context);
    void OnNodeSet (Node *node) override;

    void FixedUpdate (float time_step) override;

protected:
    AnimationController *anim_;
    AnimatedModel *head_, *body_, *eyes_, *face_detail_, *mouth_;
    AnimatedModel *shirt_, *pants_, *hat_;

    void SetModel (String model_file_path, 
            BodyPart part, 
            String material_file_path = "");

};

};
