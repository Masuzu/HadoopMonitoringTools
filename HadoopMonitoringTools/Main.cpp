#include "ResourceManagerAPI.h"

#include <iostream>
#include "json/json.h"

using namespace Hadoop::Tools;

int main()
{
	ResourceManagerAPI *resource_manager_API = new ResourceManagerAPI("http://resourcemanager.pa4.hpc.criteo.prod");
	resource_manager_API->GetAllApps({ "user=recocomputer" });

	delete resource_manager_API;
}