open PersonTypes;

open Routing;

type state = {
  saving: bool,
  item: option(person),
  fetching: bool
};

type action =
  | StartFetching
  | ErrorFetching
  | ReceiveItem(person)
  | GoBack
  | Submit(person);

let component = ReasonReact.reducerComponent("PersonEdit");

let initialState = {saving: false, fetching: false, item: None};

let url = "http://my-json-server.typicode.com/vovanmix/reason-playground/persons";

let fetch = (self: ReasonReact.self('a, 'b, 'c), id) : unit =>
  Js.Promise.(
    Axios.get(url ++ "/" ++ string_of_int(id))
    |> then_(response => response##data |> Decode.person |> resolve)
    |> then_(item => ReceiveItem(item) |> self.send |> resolve)
    |> catch(_error => ErrorFetching |> self.send |> resolve)
  )
  |> Fun.noOp;

let callSubmit = (self: ReasonReact.self('a, 'b, 'c), id, form) : unit => {
  let body = form |> Encode.person;
  Js.Promise.(
    Axios.putData(url ++ "/" ++ string_of_int(id), body)
    |> then_(response => Js.log(response) |> resolve)
    |> then_(() => GoBack |> self.send |> resolve)
    |> catch(error => Js.log(error) |> resolve)
  )
  |> Fun.noOp;
};

let make = (~id, _children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | Submit(form) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, saving: true},
        (self => callSubmit(self, id, form))
      )
    | ReceiveItem(item) =>
      ReasonReact.Update({...state, item: Some(item), fetching: false})
    | GoBack =>
      ReasonReact.SideEffects(((_) => mkSectionRoute(People, ()) |> redirect))
    | ErrorFetching => ReasonReact.Update({...state, fetching: false})
    | StartFetching =>
      ReasonReact.UpdateWithSideEffects(
        {...state, fetching: true},
        (self => fetch(self, id))
      )
    },
  didMount: self => {
    self.send(StartFetching);
    ReasonReact.NoUpdate;
  },
  render: self =>
    switch self.state.item {
    | Some(item) =>
      <PersonForm
        onSubmit=(value => Submit(value) |> self.send)
        saving=self.state.saving
        initialState=item
      />
    | None => ReasonReact.nullElement
    }
};
