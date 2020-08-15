#include "tag.h"

#include <stdlib.h>
#include <iostream>

//Helper methods for the print line strings
int indent = 0;
void printIndent(){
	for(int i = 0; i < indent;i++){
		std::cout << "     ";
	}
}


//Implementing all our methods for getting line strings
void Tag::printTag()
{
	printIndent();
	std::cout << "WRONG TAG" << std::endl;
}
std::string Tag::getLineString()
{
	return std::string("WRONG TAG METHOD");	
}

void TagByte::printTag()
{
	printIndent();
	std::cout << "\"" << *name << "\"" << " : " << this->data << std::endl;
}
std::string TagByte::getLineString()
{
	return (*name + std::string(1, this->data)); 
}

void TagShort::printTag()
{	
	printIndent();
	std::cout << "\"" << *name << "\"" << " : " << this->data << std::endl;
}
std::string TagShort::getLineString()
{
	return (*name + std::to_string(this->data));
}

void TagInt::printTag()
{
	printIndent();
	std::cout << "\"" << *name << "\"" << " : " << this->data << std::endl;
}
std::string TagInt::getLineString()
{
	return (*name + std::to_string(this->data));
}

void TagLong::printTag()
{
	printIndent();
	std::cout << "\"" << *name << "\"" << " : " << this->data << std::endl;
}
std::string TagLong::getLineString()
{
	return (*name + std::to_string(this->data));
}

void TagFloat::printTag()
{
	printIndent();
	std::cout << "\"" << *name << "\"" << " : " << this->data << std::endl;
}
std::string TagFloat::getLineString()
{
	return (*name + std::to_string(this->data));
}

void TagDouble::printTag()
{
	printIndent();
	std::cout << "\"" << *name << "\"" << " : " << this->data << std::endl;
}
std::string TagDouble::getLineString()
{
	return (*name + std::to_string(this->data));
}

void TagByteArray::printTag()
{
	printIndent(); //TODO
}
std::string TagByteArray::getLineString()
{
	return (*name + std::to_string(numberOfTags));
}

void TagString::printTag()
{
	printIndent(); //TODO
}
std::string TagString::getLineString()
{
	return (*name + *data);
}

void TagList::printTag()
{
	printIndent();	
}
std::string TagList::getLineString(){
	return (*name + std::to_string(numberOfTags));
}

void TagCompound::printTag(){
	printIndent();
	indent++;
	std::cout << "\"" << *name << "\"" << " : {" << this->tagList->size() << "}" << std::endl;
	for(int i = 0; i < this->tagList->size();i++){	
		Tag* tag = (*(this->tagList))[i];
		if(tag->tagId == 0){
			printIndent();
			std::cout << "END TAG" << std::endl;
			continue;
		}
		if(tag == NULL){
			std::cout << "NULL POINTER TO THE TAG" << std::endl;
		}else{
			tag->printTag();	
		}	
	}
	indent--;	
}
std::string TagCompound::getLineString(){
	return (*name + std::string(" {") + std::to_string(tagList->size()) + std::string("}"));
}

void TagIntArray::printTag(){
	printIndent();
}
std::string TagIntArray::getLineString(){
	return std::string("NOT YET IMPLEMENTED"); 
}


void TagLongArray::printTag(){
	printIndent();
}
std::string TagLongArray::getLineString(){
	return std::string("NOT YET IMPLEMENTED");	
}


