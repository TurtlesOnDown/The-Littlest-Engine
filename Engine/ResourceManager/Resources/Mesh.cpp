#include "Mesh.h"

Mesh::Mesh(Path &p, ResourceManager *r):Resource(p, r) {

}

Mesh::~Mesh() {

}

void Mesh::init() {
  if (initialized) return;

  initialized = true;
}

void Mesh::destroy() {

}