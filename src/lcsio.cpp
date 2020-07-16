

#define	LCSIO_CPP
#include "../includes26.h"

/*
This file is a complete rewrite of the LCS I/O system.
The original lcsio.h can be found in lcsio-old.h in the sourceforge Subversion
repository.
This file is part of Liberal Crime Squad.
	Liberal Crime Squad is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	Liberal Crime Squad is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with Liberal Crime Squad; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   02111-1307   USA
*/
bool initialized = false;
const char *art_search_paths[] =
{
   #ifdef INSTALL_DATA_DIR
   INSTALL_DATA_DIR CONST_LCS_ART,
   #endif
   #ifndef WIN32
   CONST_USR_LOCAL_SHARE_LCS_ART.c_str(),
   CONST_USR_SHARE_LCS_ART.c_str(),
   CONST_USR_GAMES_SHARE_LCS_ART.c_str(),
   CONST_USR_GAMES_LCS_ART.c_str(),
   #endif
   CONST_X_ART_FOLDER.c_str(),
   CONST_X_PARENT_ART_FOLDER.c_str(),
   NULL
};
//Check if filename exists on the system.
//Filename is the full path to the file.
//This works on directories too, but only in Linux!
bool LCSFileExists(const char* filename)
{
	struct stat st;
	return(stat(filename, &st) == 0);
}
//Put the home directory prefix in homedir.
//Create the home directory if it does not exist.
bool LCSInitHomeDir()
{
#ifndef WIN32
	char* homeenv = getenv(CONST_HOME.c_str());
#else
	char* homeenv = (char*)DOT_SLASH.c_str();
#endif
	//Do everything using STL String, it is safer that way.
	std::string str = homeenv;
	if (str[len(str) - 1] != '/')
		str += CONST_lcsio011;
#ifndef WIN32
	str += CONST_LCS;
#endif
	strncpy(homedir, str.c_str(), MAX_PATH_SIZE);
	if ((!LCSFileExists(homedir)) && (strncmp(homedir, CONST_lcsio013.c_str(), 1) != 0))
	{
#ifdef WIN32
		if (_mkdir(homedir) != 0)
			return false;
#else
		if (mkdir(homedir, 0750) != 0)
			return false;
#endif
	}
	return true;
}
//Put the art directory prefix in artdir.
bool LCSInitArtDir()
{
	const char* artprefix;
	artprefix = art_search_paths[0];
	std::string tester;
	for (int i = 1; artprefix != NULL; i++)
	{
		tester = artprefix;
		tester.append(NEWSPIC_CPC);
		if (LCSFileExists(tester.c_str()))
			break;
		artprefix = art_search_paths[i];
	}
	if (artprefix == NULL)
		return false;
	strncpy(artdir, artprefix, MAX_PATH_SIZE);
	return true;
}
void LCSRenameFile(const char* old_filename, const char* new_filename, int flags)
{
	if (!initialized)
	{
		LCSInitHomeDir();
		LCSInitArtDir();
		initialized = true;
	}
	std::string old_filepath;
	std::string new_filepath;
	if (flags & LCSIO_PRE_ART)
		old_filepath = artdir;
	else if (flags & LCSIO_PRE_HOME)
		old_filepath = homedir;
	new_filepath = old_filepath;
	old_filepath.append(old_filename);
	new_filepath.append(new_filename);
	rename(old_filepath.c_str(), new_filepath.c_str());
}
FILE* LCSOpenFile(const char* filename, const char* mode, int flags)
{
	if (!initialized)
	{
		LCSInitHomeDir();
		LCSInitArtDir();
		initialized = true;
	}
	std::string filepath;
	if (flags & LCSIO_PRE_ART)
		filepath = artdir;
	else if (flags & LCSIO_PRE_HOME)
		filepath = homedir;
	filepath.append(filename);
	return fopen(filepath.c_str(), mode);
}
vector<string> LCSSaveFiles()
{
	vector<string> save_files;
	tinydir_dir dir;
	tinydir_open(&dir, homedir);
	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if (strstr(file.name, CONST_DAT.c_str()) != NULL && strstr(file.name, CONST_SCORE.c_str()) == NULL)
			save_files.push_back(file.name);
		tinydir_next(&dir);
	}
	tinydir_close(&dir);
	return save_files;
}
//C++ file i/o version of the above.
bool LCSOpenFileCPP(std::string filename, std::ios_base::openmode mode, int flags, std::fstream &file)
{
	if (!initialized) //Check if the directories have not been initialized.
	{
		LCSInitHomeDir(); //Initialize the home directory of LCS. Where stuff like the save and score files are stored.
		LCSInitArtDir(); //Initialize the art dir.
		initialized = true; //Initialized.
	}
	std::string filepath = ""; //The actual path to the file.
	//This ifelse block decides which directory the file gets saved to.
	if (flags & LCSIO_PRE_ART) //Art dir specified.
		filepath = artdir; //Set the filepath to the artdir.
	else if (flags & LCSIO_PRE_HOME) //Home dir specified.
		filepath = homedir; //Set the filepath to the homedir.
	filepath.append(filename); //Append the file's name/relative path to the filepath.
	file.open(filepath.c_str(), mode); //Opens the file.
	return file.is_open(); //Check if file opened successfully.
}
void LCSDeleteFile(const char* filename, int flags)
{
	if (!initialized)
	{
		LCSInitHomeDir();
		LCSInitArtDir();
		initialized = true;
	}
	std::string str;
	if (flags & LCSIO_PRE_ART)
		str.append(artdir);
	else if (flags & LCSIO_PRE_HOME)
		str.append(homedir);
	str.append(filename);
	remove(str.c_str());
}
void LCSCloseFile(FILE* handle)
{
	fclose(handle);
}
//C++ file i/o version of the above.
void LCSCloseFileCPP(std::fstream &file)
{
	if (file.is_open()) //Check if the file even is open so that we don't bother closing a file that isn't open.
		file.close();
}