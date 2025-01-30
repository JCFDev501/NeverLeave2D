#include "SaveData.h"
#include <direct.h>
#include <fstream>
#include  <iostream>
#include <list>
#include <string>


SaveData::SaveData()
{
}

SaveData::~SaveData()
= default;

bool SaveData::Save()
{
	// Make sure the directory exists.
	_mkdir(s_kDirectory);

	// Combine directory and filenames.
	std::string path = s_kDirectory + std::string(s_kFileName);

	// Open the file.
	std::ofstream file;
	file.open(path, std::ios::out); // TODO: change to binary mode.
	if (!file.is_open())
	{
		std::cout << "Failed to open " << path << std::endl;
		return false;
	}

	// Write the data to the file.
	file.write((char*)(&m_data), sizeof(m_data)); // check

	// Close the file.
	file.close();

	m_data.mNumSaved++;

	return true; // we did it!!!
}

bool SaveData::Load()
{
	// Combine directory and filenames
	std::string path = s_kDirectory + std::string(s_kFileName);

	// Open the file.
	std::ifstream file;
	file.open(path, std::ios::in); // TODO: change to binary mode.
	if (!file.is_open())
	{
		std::cout << "Failed to open " << path << std::endl;
		return false;
	}

	// Read from the file.
	file.read((char*)(&m_data), sizeof(m_data)); // check

	// Close the file.
	file.close();

	// Update m_isloaded.
	m_isLoaded = true;

	return true;
}
