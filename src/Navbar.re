open Utils;

open Routing;

let component = ReasonReact.statelessComponent("Navbar");

let make = (~sections, ~route, _children) => {
  ...component,
  render: _self =>
    <div>
      <ul>
        (
          listEl(
            sections
            |> List.mapi((i, s) => {
                 let (rt, title) = s;
                 let active =
                   switch (rt, route) {
                   | (Section(a, _), Section(b, _)) => a == b
                   | _ => rt === route
                   };
                 <li key=(string_of_int(i))>
                   <Link.Text active text=title to_=rt />
                 </li>;
               })
          )
        )
      </ul>
    </div>
};
