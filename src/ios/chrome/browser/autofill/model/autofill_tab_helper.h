// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_AUTOFILL_MODEL_AUTOFILL_TAB_HELPER_H_
#define IOS_CHROME_BROWSER_AUTOFILL_MODEL_AUTOFILL_TAB_HELPER_H_

#include <memory>

#import "base/memory/raw_ptr.h"
#include "ios/web/public/web_state_observer.h"
#import "ios/web/public/web_state_user_data.h"

@class AutofillAgent;
@protocol AutofillCommands;
class ChromeBrowserState;
@protocol FormSuggestionProvider;
@class UIViewController;

namespace autofill {
class ChromeAutofillClientIOS;
}

// Class binding an instance of AutofillAgent to a WebState.
class AutofillTabHelper : public web::WebStateObserver,
                          public web::WebStateUserData<AutofillTabHelper> {
 public:
  AutofillTabHelper(const AutofillTabHelper&) = delete;
  AutofillTabHelper& operator=(const AutofillTabHelper&) = delete;

  ~AutofillTabHelper() override;

  // Sets a weak reference to the view controller used to present UI.
  void SetBaseViewController(UIViewController* base_view_controller);

  void SetCommandsHandler(id<AutofillCommands> commands_handler);

  // Returns an object that can provide Autofill suggestions.
  id<FormSuggestionProvider> GetSuggestionProvider();

  autofill::ChromeAutofillClientIOS* autofill_client() {
    return autofill_client_.get();
  }

 private:
  friend class web::WebStateUserData<AutofillTabHelper>;

  AutofillTabHelper(web::WebState* web_state);

  // web::WebStateObserver implementation.
  void WebStateDestroyed(web::WebState* web_state) override;

  // The BrowserState associated with this WebState.
  raw_ptr<ChromeBrowserState> browser_state_;

  // The Objective-C AutofillAgent instance.
  __strong AutofillAgent* autofill_agent_;

  // The iOS AutofillClient instance.
  std::unique_ptr<autofill::ChromeAutofillClientIOS> autofill_client_;

  WEB_STATE_USER_DATA_KEY_DECL();
};

#endif  // IOS_CHROME_BROWSER_AUTOFILL_MODEL_AUTOFILL_TAB_HELPER_H_
