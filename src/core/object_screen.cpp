#include "object_screen.h"
#include "scene.h"

glm::vec2 ObjectScreen::getRenderPosition() const
{
    return render_position_ / game_.getCurrentScene()->getCameraZoom();
}