import { TemplatesList } from "./templates/templates.list";

export class Renderer {

  private templateContextFunctions = {
    include: (template, context) => {
      try {
        return this.compileTemplate(TemplatesList[template], context)
      } catch (e) {
        return `<pre>${e.message}\n${e.stack.split('\n').map(function (line) { return line.trim(); })}</pre>`;
      }
    },
    keyToId: (key: string) => {
      return key.split('.').join('_');
    },
    compile: this.compileTemplate.bind(this),
  };

  private static escapeHTML(string) {
    string = `${string}`;
    return string.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  }

  private compileTemplate(template: string, context: any = {}) {
    return template
      .replace(/#if\s+(?<label>[a-zA-Z]+?)\s*\((?<if>.+?)\)(?<code>(?:.|\n)*)#end\k<label>(?=\s+$)/igm, (match: string, ...groups:any[]) => {
        let named = groups[5];
        return this.evalTemplateCode(named.if.trim(), context) ? this.compileTemplate(named.code, context) : '';
      })
      .replace(
        /#foreach\s+(?<label>[a-zA-Z]+?)\s*\((?<array>.+?)\s+as\s+(?<item>[a-zA-Z][a-zA-Z0-9_]*)(?:\s*,\s*(?<key>[a-zA-Z][a-zA-Z0-9_]*))?\)(?<code>(?:.|\n)*)#end\k<label>/igm,
        (match: string, ...groups:any[]) => {
          let named = groups[7];

        const iterator = this.evalTemplateCode(named.array.trim(), context);
        if (!iterator) {
          return '';
        }
        let value = '';
        for (let key in iterator) {
          if (!iterator.hasOwnProperty(key)) {
            continue;
          }
          context[named.item.trim()] = iterator[key];
          if (named.key) {
            context[named.key.trim()] = key;
          }
          value += this.compileTemplate(named.code, context);
        }

        context[named.item] = undefined;
        if (named.key) {
          context[named.key.trim()] = undefined;
        }
        return value;
      })
      .replace(/\{\%\s*?(.+?)\s*?\%\}/ig, (match: string, code: string) => {
        return this.evalTemplateCode(code.trim(), context);
      })
      .replace(/\{\{\s*?(.+?)\s*?\}\}/ig, (match: string, key: string) => {
        return Renderer.escapeHTML(this.evalTemplateCode(`context.${key}`, context));
      });
  }

  private evalTemplateCode(js, context) {
    //# Return the results of the in-line anonymous function we .call with the passed context
    return function () {
      return eval(`var engine = this.engine; var context = this.context; ${js}`);
    }.call({
      engine: this.templateContextFunctions,
      context: context,
    });
  }

  public render(name: string, context: any = {}): HTMLElement {
    const html = this.compileTemplate(TemplatesList[name], context);

    const div = document.createElement('div');
    div.innerHTML = html;
    return div;
  }
}
