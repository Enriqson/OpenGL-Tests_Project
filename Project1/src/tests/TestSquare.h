#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include <memory>


namespace test {
	class TestSquare : public Test
	{
	public:
		TestSquare();
		~TestSquare();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_Ib;
		std::unique_ptr<VertexBuffer> m_Vb;
		float m_SquareColor[4];
		float m_BackgroundColor[4];
		glm::vec3 m_TranslationA;
		glm::mat4 m_Proj, m_View;
	};
}
