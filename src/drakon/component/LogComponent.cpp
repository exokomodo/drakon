#include <drakon/_component/LogComponent.h>

drakon::component::LogComponent::LogComponent(const std::string_view _message,
                                              const bool _isOneShot)
    : message(_message), isOneShot(_isOneShot) {}
