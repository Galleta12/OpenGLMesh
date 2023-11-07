#pragma once

#include<json/json.h>
#include "Game.h"

#include "ECS.h"
#include "Components.h"
#include "IncludesForMath.h"

using json = nlohmann::json;


class Model : public Entity
{
	public:

		Model(Manager& mManger, const char* file);
		~Model();

		void draw(Shader &shader) override;

	private:

		const char* mFile;
		
		std::vector<unsigned char> mDataModel;
		
		std::vector<unsigned char> getMeshData();


		std::vector<float> getAccessorFloats(json accesorNode);
		std::vector<GLuint> getAccessorIndices(json accesorNode);

		


		//return type of data to the accesots
		std::vector<glm::vec2> saveFloatsVec2(std::vector<float> floatVec);
		std::vector<glm::vec3> saveFloatsVec3(std::vector<float> floatVec);
		std::vector<glm::vec4> saveFloatsVec4(std::vector<float> floatVec);

		
		json JSON;



};