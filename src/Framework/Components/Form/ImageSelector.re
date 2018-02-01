let component = ReasonReact.statelessComponent("FileSelector");

let isValidSize = (file: FileReaderInput.file) => {
  let maxSize = 3000000;
  file.size <= maxSize;
};

let isValidMime = (file: FileReaderInput.file) : bool => {
  let mimeTypes = ["image/jpeg", "image/png", "image/svg+xml"];
  let mime = file.type_;
  List.mem(mime, mimeTypes);
};

let isValidFile = (file: FileReaderInput.file) => {
  let validSize = isValidSize(file);
  let validMime = isValidMime(file);
  if (validSize == false) {
    ();
      /* TODO: error message: Cannot process the file, it is too big! */
  };
  if (validMime == false) {
    ();
      /* TODO: error message: File format is not supported! */
  };
  validSize && validMime;
};

let make =
    (
      ~value: option(string),
      ~onChange: option(string) => unit,
      ~accept=".jpg, .png",
      ~placeholder="Click to select an image",
      _children
    ) => {
  /*  */
  let handleFileChange = (files: array(FileReaderInput.fileResult)) : unit =>
    MyArray.head(files)
    |> Option.filter((res: FileReaderInput.fileResult) => isValidFile(res.file))
    |> Option.andThen((res: FileReaderInput.fileResult) =>
         Some(res.result) |> onChange
       );
  /*  */
  let handleFileClear = (_) : unit => None |> onChange;
  /*  */
  {
    ...component,
    render: _self =>
      <div className="row">
        <div className="col-md-3">
          <FileReaderInput
            accept as_="url" className="form-control" onChange=handleFileChange>
            <button> (ReasonReact.stringToElement(placeholder)) </button>
          </FileReaderInput>
        </div>
        <div className="col-md-6">
          (
            switch value {
            | None => ReasonReact.nullElement
            | Some(v) =>
              <img
                alt="something cool"
                style=(
                  ReactDOMRe.Style.make(~maxWidth="100%", ~maxHeight="100px", ())
                )
                src=v
              />
            }
          )
        </div>
        <div className="col-md-3">
          (
            switch value {
            | None => ReasonReact.nullElement
            | Some(_) =>
              <button
                className="btn btn-info" _type="button" onClick=handleFileClear>
                <i className="fa fa-times" />
                (ReasonReact.stringToElement("Clear"))
              </button>
            }
          )
        </div>
      </div>
  };
};
