open PersonTypes;

type state = {
  items: list(person),
  fetching: bool,
  error: option(string)
};

type action =
  | StartFetching
  | ErrorFetching
  | ReceiveItems(list(person));

let component = ReasonReact.reducerComponent("List");

let initialState = {items: [], fetching: false, error: None};

let url = "http://my-json-server.typicode.com/vovanmix/reason-playground/persons";

let fetch = (self: ReasonReact.self('a, 'b, 'c)) : unit =>
  Js.Promise.(
    Axios.get(url)
    |> then_(response => response##data |> Decode.persons |> resolve)
    |> then_(items => ReceiveItems(items) |> self.send |> resolve)
    |> catch(_error => ErrorFetching |> self.send |> resolve)
  )
  |> Fun.noOp;

let make = (~qs, _children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | ReceiveItems(items) =>
      ReasonReact.Update({items, fetching: false, error: None})
    | ErrorFetching =>
      ReasonReact.Update({
        ...state,
        fetching: false,
        error: Some("Cannot fetch data...")
      })
    | StartFetching =>
      ReasonReact.UpdateWithSideEffects(
        {...state, fetching: true, error: None},
        (self => fetch(self))
      )
    },
  didMount: self => {
    self.send(StartFetching);
    ReasonReact.NoUpdate;
  },
  render: self =>
    <div>
      <h2> (ReasonReact.stringToElement("People")) </h2>
      (
        self.state.error != None ?
          <div>
            (ReasonReact.stringToElement(self.state.error |> Option.getOrElse("")))
          </div> :
          ReasonReact.nullElement
      )
      <div>
        (
          ReasonReact.stringToElement(
            self.state.fetching ? "fetching" : "not fetching"
          )
        )
      </div>
      <div>
        (
          self.state.items
          |> List.mapi((idx, item) =>
               <PersonListItem item key=(idx |> string_of_int) />
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
    </div>
};
