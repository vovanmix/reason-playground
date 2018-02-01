open PersonTypes;

let component = ReasonReact.statelessComponent("PersonListItem");

let make = (~item: person, _children) => {
  ...component,
  render: _self =>
    <div>
      <div> (ReasonReact.stringToElement(item.name)) </div>
      <div>
        (
          ReasonReact.stringToElement(
            Option.getOrElse("None", Option.map(string_of_int, item.id))
          )
        )
      </div>
    </div>
};
