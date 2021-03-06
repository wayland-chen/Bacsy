/*
 * Copyright (C) 2011  Ives van der Flaas
 * Copyright (C) 2011  Nathan Samson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <list>
#include <functional>
#include <fstream>
#include <algorithm>
#include "Bacsy/Client/BackupEngine.h"

namespace Bacsy
{
namespace Client
{

using namespace Common;
using namespace Rules;

class SourceNameToSourcer
{
public:
	SourceNameToSourcer(
			const CascadingSourceConfiguration& configuration,
			Poco::ThreadPool& threadPool,
			PreviousRunRecordFactory& prrf): 
		configuration(configuration),
		threadPool(threadPool),
		prrf(prrf)
	{
	}

	Source* operator()(const std::string& sourceName)
	{
		return new Source(
				configuration.getSource(sourceName),
				threadPool,
				prrf);
	}

private:
	const CascadingSourceConfiguration& configuration;
	Poco::ThreadPool& threadPool;
	PreviousRunRecordFactory& prrf;
};

std::vector<Source*> sourceNamesToSources(
		const std::list<std::string>& sourceStrings,
		const CascadingSourceConfiguration& configuration,
		Poco::ThreadPool&  threadPool,
		PreviousRunRecordFactory& previousRunRecordFactory)
{
	std::vector<Source*> sources;
	sources.resize(sourceStrings.size());


	SourceNameToSourcer sourceNameToSource(
			configuration,
			threadPool,
			previousRunRecordFactory);

	std::transform(
			sourceStrings.begin(),
			sourceStrings.end(),
			sources.begin(),
			sourceNameToSource);
			

	return sources;
}

BackupEngine::BackupEngine(
		const CascadingSourceConfiguration& configuration,
		PreviousRunRecordFactory& previousRunRecordFactory):
	configuration(configuration),
	sources(sourceNamesToSources(
				configuration.getSources(),
				configuration,
				threadPool,
				previousRunRecordFactory)),
	previousRunRecordFactory(previousRunRecordFactory)
{
}

BackupEngine::~BackupEngine()
{
	for(std::vector<Source*>::iterator it = sources.begin();
			it != sources.end();
			it++)
	{
		delete *it;
	}
}

void BackupEngine::start()
{
	for(std::vector<Source*>::iterator it = sources.begin();
			it != sources.end();
			it++)
	{
		(*it)->start();
	}
}

void BackupEngine::joinAll()
{
	threadPool.joinAll();
}

}
}
