////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (https://ultraschall.fm)
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__
#define __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

class ICustomAction;

/// @brief The CustomActionFactory class implements a simple factory for custom actions.
class CustomActionFactory
{
public:
   /// @brief Returns the singleton instance of the CustomActionFactory class.
   /// @return <b>CustomActionFactory&</b> The singleton instance of the CustomActionFactory class.
   static CustomActionFactory& Instance();

   /// @brief Defines the function signature for creating custom actions.
   typedef ICustomAction* (*CREATE_CUSTOM_ACTION_FUNCTION)();

   /// @brief Registers a custom action with the factory.
   /// @param id The unique identifier of the custom action.
   /// @param pfn The function that creates the custom action.
   /// @return <b>ServiceStatus</b> The status of the operation.
   ServiceStatus RegisterCustomAction(const UnicodeString& id, CREATE_CUSTOM_ACTION_FUNCTION pfn);

   /// @brief Unregisters a custom action from the factory.
   /// @param id The unique identifier of the custom action.
   void UnregisterCustomAction(const UnicodeString& id);

   /// @brief Unregisters all custom actions from the factory.
   void UnregisterAllCustomActions();

   /// @brief Creates a custom action with the specified unique identifier.
   /// @param id The unique identifier of the custom action.
   /// @param pCustomAction The custom action that has been created.
   /// @return <b>ServiceStatus</b> The status of the operation.
   ServiceStatus CreateCustomAction(const UnicodeString& id, ICustomAction*& pCustomAction) const;

protected:
   virtual ~CustomActionFactory();

private:
   CustomActionFactory();

   CustomActionFactory(const CustomActionFactory&);
   CustomActionFactory& operator=(const CustomActionFactory&);

   typedef std::map<UnicodeString, CREATE_CUSTOM_ACTION_FUNCTION> FunctionDictionary;
   FunctionDictionary functions_;
   mutable std::recursive_mutex functionsLock_;
};

/// @brief The DeclareCustomAction class template simplifies the registration of custom actions.
template<class C> class DeclareCustomAction
{
public:
   /// @brief Defines the custom action type
   typedef C custom_action_type;

   /// @brief Initializes the custom action factory with the custom action type.
   DeclareCustomAction()
   {
      CustomActionFactory& factory = CustomActionFactory::Instance();
      factory.RegisterCustomAction(custom_action_type::UniqueId(), custom_action_type::CreateCustomAction);
   }

   /// @brief Unregisters the custom action type from the custom action factory.
   virtual ~DeclareCustomAction()
   {
      CustomActionFactory& factory = CustomActionFactory::Instance();
      factory.UnregisterCustomAction(custom_action_type::UniqueId());
   }
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__
