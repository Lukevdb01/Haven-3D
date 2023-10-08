#ifndef MESH_CLASS_H

#include <string>

#include "../buffers/VAO.h"
#include "../buffers/EBO.h"
#include "../camera/Camera.h"
#include "../textures/Texture.h"
#include "../Core.h"

namespace Engine::Model_Loader {

	using namespace Buffers;
	using namespace Textures;
	using namespace View;
	using namespace Shaders;

	class ENGINE_API Mesh {
	public:
		std::vector <Vertex> vertices;
		std::vector <GLuint> indices;
		std::vector <Texture> textures;

		VAO VAO;
		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
		void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1.0f),glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
	};
}

#endif // !MESH_CLASS_H
