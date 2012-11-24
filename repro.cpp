// repro.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "mono.lib")
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/exception.h>
#include <mono/metadata/mono-debug.h>


void main(int argc, char* argv[])
{
	mono_set_dirs("lib", "");
	mono_config_parse(NULL);

	MonoDomain* domain = mono_jit_init("managed.exe");
	if(!domain)
	{
		printf("Unable to initialize mono jit.\n");
		return;
	}
	MonoAssembly* assembly = mono_domain_assembly_open(domain, "managed.exe");
	if (!assembly)
	{
		printf("Unable to open assembly.\n");
		return;
	}
	
	char* argvv[1] = { "managed" };
	mono_jit_exec(domain, assembly, 1, argvv);
	
	mono_jit_cleanup(domain);

	return;
}

