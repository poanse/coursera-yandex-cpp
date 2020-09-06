#pragma once
#include "requests.h"
#include "json.h"

#include <variant>

AddRequestPtr GetAddRequestFromJson(const Json::Node& node);
GetRequestPtr GetGetRequestFromJson(const Json::Node& node);
RoutingSettings GetRoutingSettingsFromJson(const Json::Node& node);