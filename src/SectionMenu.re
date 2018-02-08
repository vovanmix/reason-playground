open Utils;

open Routing;

let component = ReasonReact.statelessComponent("SectionMenu");

let make = (~items, ~path, _children) => {
  ...component,
  render: _self =>
    <div className="section-menu">
      <ul>
        (
          listEl(
            items
            |> List.mapi((i, s) => {
                 let (sectionRoute, title) = s;
                 let active =
                   switch sectionRoute {
                   | Section(_, sectionPath) => sectionPathEqual(sectionPath, path)
                   | _ => false
                   };
                 <li key=(string_of_int(i))>
                   <Link.Text active text=title to_=sectionRoute />
                 </li>;
               })
          )
        )
      </ul>
    </div>
};
