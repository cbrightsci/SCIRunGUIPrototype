#ifndef IAUNS_RENDER_COMPONENT_STATIC_IBO_MAN_HPP
#define IAUNS_RENDER_COMPONENT_STATIC_IBO_MAN_HPP

#include <memory>
#include <es-cereal/ComponentSerialize.hpp>
#include "../IBOMan.hpp"

namespace ren {

struct StaticIBOMan
{
  // -- Data --
  std::unique_ptr<IBOMan> instance;

  // -- Functions --
  StaticIBOMan() : instance(new IBOMan) {}
  StaticIBOMan(const StaticIBOMan&) : instance(new IBOMan) {}
  StaticIBOMan(StaticIBOMan&& o) : instance(std::move(o.instance)) {}
  StaticIBOMan& operator=(const StaticIBOMan&) {return *this;}

  static const char* getName() {return "ren:StaticIBOMan";}

  bool serialize(CPM_ES_CEREAL_NS::ComponentSerialize& /* s */, uint64_t /* entityID */)
  {
    // No need to serialize.
    return true;
  }
};

} // namespace ren

#endif 
