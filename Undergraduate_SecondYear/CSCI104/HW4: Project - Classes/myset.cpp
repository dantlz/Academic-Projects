#include "myset.h"
#include "webpage.h"

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other){
	iterator it;
	iterator it2;
	MySetString newSet;

	for(it = this->begin();it != this->end();++it){
		for(it2=other.begin();it2 != other.end();++it2){
			if(*it==*it2){
				newSet.insert(*it);
			}
		}
	}

	return newSet;
}

MySetString MySetString::set_union(const MySetString& other){
	iterator it;
	iterator it2;
	MySetString newSet;

	for(it = this->begin();it != this->end();++it){
		newSet.insert(*it);
	}
	for(it2=other.begin();it2 != other.end();++it2){
		if(newSet.count(*it2)==0){
			newSet.insert(*it2);
		}
	}

	return newSet;
}

//Consider doing pointer comparison instead of deep comparison

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other){
	iterator it;
	iterator it2;
	MySetWebPage newSet;

	for(it = this->begin();it != this->end();++it){
		for(it2=other.begin();it2 != other.end();++it2){
			if(*it==*it2){
				newSet.insert(*it);
			}
		}
	}

	return newSet;
}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other){
	iterator it;
	iterator it2;
	MySetWebPage newSet;

	for(it = this->begin();it != this->end();++it){
		newSet.insert(*it);
	}
	for(it2=other.begin();it2 != other.end();++it2){
		if(newSet.count(*it2)==0){
			newSet.insert(*it2);
		}
	}

	return newSet;
}
