open PersonTypes;

type state = {saving: bool};

type action =
  | Submit(person);

let component = ReasonReact.reducerComponent("PersonCreate");

let countries: array(ReactSelect.reactSelectOption(int)) = [|
  {"value": 1, "label": "opt one"},
  {"value": 2, "label": "opt two"},
  {"value": 2, "label": "opt three"}
|];

let initialState = {saving: false};

let initialFormState: person = {
  id: None,
  country: 0,
  name: "",
  enabled: false,
  addresses: [{street: "Elm st", zip: 10342}],
  file: None,
  created_at: None
};

let callSubmit = form : unit => {
  Js.log("submit!");
  Js.log(form);
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | Submit(form) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, saving: true},
        ((_) => callSubmit(form))
      )
    },
  render: self =>
    <PersonForm
      onSubmit=(value => Submit(value) |> self.send)
      saving=self.state.saving
      countries
      initialState=initialFormState
    />
};
