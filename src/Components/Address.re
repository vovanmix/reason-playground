let component = ReasonReact.statelessComponent("Address");

type action =
  | UpdateStreet(string)
  | UpdateZip(string);

let make = (~address: Types.address, ~onChange, _children) => {
  let handleChange = action =>
    switch action {
    | UpdateStreet(street) => {...address, street} |> onChange
    | UpdateZip(zip) =>
      switch (int_of_string(zip)) {
      | zipInt => {...address, zip: zipInt} |> onChange
      | exception _ => {...address, zip: 0} |> onChange
      }
    };
  {
    ...component,
    render: _self =>
      <div>
        <fieldset className="form-group">
          <Text
            value=address.street
            onChange=(value => UpdateStreet(value) |> handleChange)
            placeholder="Name"
          />
        </fieldset>
        <fieldset className="form-group">
          <Text
            value=(string_of_int(address.zip))
            onChange=(value => UpdateZip(value) |> handleChange)
            placeholder="Name"
          />
        </fieldset>
      </div>
  };
};
