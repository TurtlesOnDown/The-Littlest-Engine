#include "Material.h"

Material::Material(Path &p, ResourceManager *r):Resource(p, r) {

}

Material::~Material() {

}

void Material::init() {
  if (initialized) return;

  initialized = true;
}

void Material::destroy() {

}