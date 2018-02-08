open PersonTypes;

open Routing;

type state = {saving: bool};

type action =
  | GoBack
  | Submit(person);

let component = ReasonReact.reducerComponent("PersonCreate");

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

let url = "http://my-json-server.typicode.com/vovanmix/reason-playground/persons";

let callSubmit = (self: ReasonReact.self('a, 'b, 'c), form) : unit => {
  let body = form |> Encode.person;
  Js.Promise.(
    Axios.postData(url, body)
    |> then_(response => Js.log(response) |> resolve)
    |> then_(() => GoBack |> self.send |> resolve)
    |> catch(error => Js.log(error) |> resolve)
  )
  |> Fun.noOp;
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, _state) =>
    switch action {
    | Submit(form) =>
      ReasonReact.UpdateWithSideEffects(
        {saving: true},
        (self => callSubmit(self, form))
      )
    | GoBack =>
      ReasonReact.SideEffects(((_) => mkSectionRoute(People, ()) |> redirect))
    },
  render: self =>
    <PersonForm
      onSubmit=(value => Submit(value) |> self.send)
      saving=self.state.saving
      initialState=initialFormState
    />
};
