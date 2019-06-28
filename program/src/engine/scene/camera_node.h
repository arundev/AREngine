#ifndef ENGINE_SCENE_CAMERA_H
#define ENGINE_SCENE_CAMERA_H

#include "node.h"
#include "../camera/camera.h"

namespace engine {
	class Camera : public Node {
	public:
		Camera();
		~Camera();

		virtual void Update(float elapse);
		virtual void Render();

		BaseCamera* camera_data()const { return camera_data_; }
		void set_camera_data(BaseCamera* camera);

		void get_view_matrix(engine::Matrix* mat) { return camera_data_->GetViewMatrix(mat); }

	private:
		BaseCamera* camera_data_;
	}; 
}

#endif // ENGINE_SCENE_CAMERA_H