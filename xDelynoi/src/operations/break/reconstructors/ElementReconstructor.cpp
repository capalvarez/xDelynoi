#include <xDelynoi/operations/break/reconstructors/ElementReconstructor.h>

ElementReconstructor::ElementReconstructor(ElementConstructor *constructor) {
    this->constructor = constructor;
}
