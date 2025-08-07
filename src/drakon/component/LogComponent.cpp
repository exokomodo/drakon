#include <drakon/_component/LogComponent.h>

drakon::component::LogComponent::LogComponent(std::string_view _message)
    : message(_message) {}
drakon::component::LogComponent::LogComponent(std::string_view _message,
                                              bool _isOneShot)
    : message(_message), isOneShot(_isOneShot) {}
