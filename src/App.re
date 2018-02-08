open Routing;

type state = {route};

type action =
  | ChangeRoute(ReasonReact.Router.url);

let component = ReasonReact.reducerComponent("App");

let initialState = {route: Index};

let sections = [(Index, "Home"), (mkSectionRoute(People, ()), "People")];

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, _state) =>
    switch action {
    | ChangeRoute(url) => ReasonReact.Update({route: url |> mapUrlToRoute})
    },
  subscriptions: self => [
    Sub(
      () => ReasonReact.Router.watchUrl(url => self.send(ChangeRoute(url))),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self => {
    let route = self.state.route;
    <div>
      <Navbar route sections />
      (
        switch route {
        | Index => <IndexPage />
        | Login => <IndexPage />
        | Section(People, path) => <PersonSection path />
        | NotFound(path) => <NotFoundPage path />
        }
      )
      <Footer />
    </div>;
  }
};
