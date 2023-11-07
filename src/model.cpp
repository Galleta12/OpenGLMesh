#include "Model.h"


std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}



Model::Model(Manager &mManger, const char *file)
:Entity(mManger)
{

    std::string text = get_file_contents(file);
	JSON = json::parse(text);
    
    // Get the binary data
	mFile = file;
	mDataModel = getMeshData();

}

Model::~Model()
{
}

void Model::draw(Shader &shader)
{
}

std::vector<unsigned char> Model::getMeshData()
{
    //store the data of te .bin file
    std::string bytesText;

    //the data about the .bin is on the json file that we saved before
    //this is the keys to get the .bin file
    std::string uri = JSON["buffers"][0]["uri"];


    std::string fileStr = std::string(mFile);

    //the bin file is stored on the same root as the parent foler of the son
    std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
    bytesText = get_file_contents((fileDirectory + uri).c_str());

    //std::cout << "file dir: " << (fileDirectory + uri).c_str() << std::endl;
    //saved in a vector of char, since the it was stored as bytes
	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
	return data;
}

std::vector<float> Model::getAccessorFloats(json accesorNode)
{
    

    std::vector<float> floatVec;

	// get the type the buffer view and properties from the accessor node
    //with the value we are going to get the value inside the key, otherwise, if it doesnt exist, we just use the second parameter
	
    //point to the current bufferview
    unsigned int buffViewInd = accesorNode.value("bufferView", 1);
	
    //how many data, we have to get from the current bufferviewnode
    unsigned int count = accesorNode["count"];
    //this tell the indes where we need to look for data in respecto to the current buffer view
	unsigned int accByteOffset = accesorNode.value("byteOffset", 0);
    
    
    //how to save the float, float 2, float 3
	std::string type = accesorNode["type"];

    
     
    json bufferViewNode = JSON["bufferViews"][buffViewInd];
	//this tell where the buffer view start
    //two different offset, since sometimes two differen accessor share the same buffer view
    //for example a flot 3 buffer view could be share by a position accessor and normal accessor
    unsigned int byteOffset = bufferViewNode["byteOffset"];


    int typeBuffer;
	
    if (type == "SCALAR") typeBuffer = 1;
	else if (type == "VEC2") typeBuffer = 2;
	else if (type == "VEC3") typeBuffer = 3;
	else if (type == "VEC4") typeBuffer = 4;
	else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");


    //start from the beginning
    unsigned int beginningOfData = byteOffset + accByteOffset;
	unsigned int lengthOfData = count * 4 * typeBuffer;

    //these will tell where we should start looking, the current index in the jsondatastructure
	for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i)
	{
		unsigned char bytes[] = { mDataModel[i++], mDataModel[i++], mDataModel[i++], mDataModel[i++] };
		float value;
		//trasform bytes into float
        std::memcpy(&value, bytes, sizeof(float));
		
        floatVec.push_back(value);
	}

	return floatVec;





}

std::vector<GLuint> Model::getAccessorIndices(json accesorNode)
{
    std::vector<GLuint> indices;

	// Get properties from the accessor
	unsigned int buffViewInd = accesorNode.value("bufferView", 0);
	unsigned int count = accesorNode["count"];
	unsigned int accByteOffset = accesorNode.value("byteOffset", 0);
	unsigned int componentType = accesorNode["componentType"];

	// Get properties from the bufferView
	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	// Get indices with regards to their type: unsigned int, unsigned short, or short
	unsigned int beginningOfData = byteOffset + accByteOffset;



    //the indices are not stored in the vertices, not like the buffer, thus
    //check th


    //unsigend intiger
	if (componentType == 5125)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i)
		{
			unsigned char bytes[] = { mDataModel[i++], mDataModel[i++], mDataModel[i++], mDataModel[i++] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	
    //unsigend short
    else if (componentType == 5123)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
		{
			unsigned char bytes[] = { mDataModel[i++], mDataModel[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}

    //type short
	else if (componentType == 5122)
	{
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i)
		{
			unsigned char bytes[] = { mDataModel[i++], mDataModel[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}

	return indices;
}







std::vector<glm::vec2> Model::saveFloatsVec2(std::vector<float> floatVec)
{
    std::vector<glm::vec2> vectors;
	for (int i = 0; i < floatVec.size(); i)
	{
		vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec3> Model::saveFloatsVec3(std::vector<float> floatVec)
{
    std::vector<glm::vec3> vectors;
	for (int i = 0; i < floatVec.size(); i)
	{
		vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec4> Model::saveFloatsVec4(std::vector<float> floatVec)
{
    std::vector<glm::vec4> vectors;
	for (int i = 0; i < floatVec.size(); i)
	{
		vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;
}
