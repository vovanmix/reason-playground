open Routing;

let component = ReasonReact.statelessComponent("PersonSection");

let items = [
  (mkSectionRoute(People, ()), "List"),
  (mkSectionRoute(People, ~action="create", ()), "Create")
];

let make = (~path: RoutingUtils.sectionPath, _children) => {
  ...component,
  render: _self =>
    <div>
      <SectionMenu items path />
      (
        switch path {
        | {action: Some("create")} => <PersonCreate />
        | {id: Some(id)} => <PersonEdit id />
        | {action: None, id: None, qs} => <PersonList qs />
        | _ => <NotFoundPage path=[] />
        }
      )
    </div>
};
