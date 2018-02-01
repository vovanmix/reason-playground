let component = ReasonReact.statelessComponent("FormList");

type action('a) =
  | Update('a, int)
  | Remove(int)
  | Add;

/* TODO: | Reorder */
let make =
    (~items: list('a), ~onChange, ~label, ~defaultValue, ~renderItem, _children) => {
  let handleChange = action =>
    switch action {
    | Update(item, idx) =>
      List.mapi((i, record) => i == idx ? item : record, items) |> onChange
    | Add => items @ [defaultValue] |> onChange
    | Remove(idx) =>
      let elt = List.nth(items, idx);
      List.filter(addr => addr !== elt, items) |> onChange;
    };
  /*  */
  let elements =
    items
    |> List.mapi((i, item) => {
         let elt = renderItem(item, value => Update(value, i) |> handleChange);
         <div key=(string_of_int(i))>
           <div> elt </div>
           <button onClick=(_e => Remove(i) |> handleChange)>
             (ReasonReact.stringToElement("x"))
           </button>
         </div>;
       });
  {
    ...component,
    render: _self =>
      <div>
        <h2> (ReasonReact.stringToElement(label)) </h2>
        <div> (elements |> Array.of_list |> ReasonReact.arrayToElement) </div>
        <button onClick=(_e => Add |> handleChange)>
          (ReasonReact.stringToElement("Add more"))
        </button>
      </div>
  };
};
