#include "TestSquare.h"

#include "imgui\imgui.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

namespace test {

	TestSquare::TestSquare()
		: m_SquareColor{ 1.0f,1.0f,1.0f,1.0f }, m_BackgroundColor{ 0.0f,0.0f,0.0f,0.0f },
		m_TranslationA(200, 200, 0),
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-50.0f, -50.0f,
			 50.0f, -50.0f,
			 50.0f,  50.0f,
			-50.0f,  50.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();
		m_Vb = std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float));
		m_Ib = std::make_unique<IndexBuffer>(indices, 6 * sizeof(unsigned int));
		m_Shader = std::make_unique<Shader>("res/shaders/TestSquare.shader");

		VertexBufferLayout layout;
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_Vb, layout);

		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", m_SquareColor[0], m_SquareColor[1], m_SquareColor[2], m_SquareColor[3]);
	}
	TestSquare::~TestSquare()
	{

	}

	void TestSquare::OnUpdate(float deltaTime)
	{

	}
	void TestSquare::OnRender()
	{
		GLCall(glClearColor(m_BackgroundColor[0], m_BackgroundColor[1], m_BackgroundColor[2], m_BackgroundColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniform4f("u_Color", m_SquareColor[0], m_SquareColor[1], m_SquareColor[2], m_SquareColor[3]);
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_Ib, *m_Shader);
		}
	}
	void TestSquare::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::ColorEdit4("Square Color", m_SquareColor);
		ImGui::ColorEdit4("Background Color", m_BackgroundColor);

	}
}