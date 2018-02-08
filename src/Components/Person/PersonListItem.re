open Utils;

open Routing;

open PersonTypes;

let component = ReasonReact.statelessComponent("PersonListItem");

let make = (~item: person, _children) => {
  ...component,
  render: _self =>
    <div>
      <div> (textEl(item.name)) </div>
      <div> (textEl(stringifyId(item.id))) </div>
      <div>
        <Link.Button
          to_=(mkSectionRoute(People, ~id=item.id, ()))
          text="Edit"
          icon="pen"
        />
      </div>
    </div>
};
