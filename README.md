# Bill Tracker
Small project where one can enter all their bills and generate an expense overview.
This is mainly used as a playground for some Qt6 experience.

## UI
Every widget is set up in a model/view layout. 
The view is responsible for handling the UI while the job of the model is to manage the data.
User input from the UI is immediately passed from the view to the model where it is processed.

### Design rules
This design has a couple of rules as a consequence.
- The view classes do not call any library functions. This is always done in the model.
- The API of the model classes are fully standard (i.e. don't use QString, CString, etc. Types defined in the lib are ok)
