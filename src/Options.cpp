#include "Options.h"

#include "WindowOptions.h"

const Options& getOptions()
{
	static Options options;
	if (!options.initialized)
	{
		// TODO: Load options from file at first use
		options.initialized = true;
	}
	return options;
}
