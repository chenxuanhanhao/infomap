/**********************************************************************************

 Infomap software package for multi-level network clustering

 Copyright (c) 2013 Daniel Edler, Martin Rosvall
 
 For more information, see <http://www.mapequation.org>
 

 This file is part of Infomap software package.

 Infomap software package is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Infomap software package is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with Infomap software package.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************/


#include "InfomapContext.h"
#include "flowData_traits.h"
#include "InfomapGreedySpecialized.h"

// InfomapFactory::create(const Config& config)
// {
// 	if (config.isUndirected())
// 		return std::auto_ptr<InfomapBase>(new InfomapGreedySpecialized<InfomapType<FlowUndirected, WithMemory> >(m_config));
// 	if (m_config.undirdir || m_config.outdirdir || m_config.rawdir)
// 		return std::auto_ptr<InfomapBase>(new InfomapGreedySpecialized<InfomapType<FlowDirectedNonDetailedBalance, WithMemory> >(m_config));
// 	if (m_config.recordedTeleportation)
// 		return std::auto_ptr<InfomapBase>(new InfomapGreedySpecialized<InfomapType<FlowDirectedWithTeleportation, WithMemory> >(m_config));
// 	// unrecorded teleportation
// 	return std::auto_ptr<InfomapBase>(new InfomapGreedySpecialized<InfomapType<FlowDirectedNonDetailedBalanceWithTeleportation, WithMemory> >(m_config));

// }

InfomapContext::InfomapContext(const Config& config)
: m_config(config)
{
	if (config.isMemoryNetwork())
		createInfomap<WithMemory>();
	else
		createInfomap<WithoutMemory>();
}

template<typename NetworkType>
void InfomapContext::createInfomap()
{
	if (m_config.isUndirected())
		m_infomap = std::auto_ptr<InfomapBase>(new InfomapGreedyType<InfomapType<FlowUndirected, NetworkType> >(m_config));
	else if (m_config.undirdir || m_config.outdirdir || m_config.rawdir)
		m_infomap = std::auto_ptr<InfomapBase>(new InfomapGreedyType<InfomapType<FlowDirectedNonDetailedBalance, NetworkType> >(m_config));
	else if (m_config.recordedTeleportation)
		m_infomap = std::auto_ptr<InfomapBase>(new InfomapGreedyType<InfomapType<FlowDirectedWithTeleportation, NetworkType> >(m_config));
	else // unrecorded teleportation
		m_infomap = std::auto_ptr<InfomapBase>(new InfomapGreedyType<InfomapType<FlowDirectedNonDetailedBalanceWithTeleportation, NetworkType> >(m_config));
}
